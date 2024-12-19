import {ArtObjectType, ShapePosition, ShapeSize} from '../types/shapes'
import {BaseShape, IShape} from './Shape/BaseShape'
import {ShapeFactory} from './ShapeFactory'

type ChangeEvent = 'create' | 'update' | 'delete'

type ShapeChangeObserver = (shapeId: string, event: ChangeEvent) => void

type ICanvasModel = {
	getShape: (shapeId: string) => IShape,
	getCanvasSize: () => ShapeSize,
	getShapeIdToShapeMap: () => Map<string, IShape>,
	serializeCanvasToJson: () => string,
}

class CanvasModel implements ICanvasModel {
	private canvasSize: ShapeSize = {width: 800, height: 600}
	private shapes: Map<string, BaseShape> = new Map()
	private shapeChangeObservers: ShapeChangeObserver[] = []

	addArtObject(type: ArtObjectType): void {
		this.addShape(ShapeFactory.constructShape(type))
	}

	addImage(data: string) {
		this.addShape(ShapeFactory.constructShape('image', data))
	}

	updateShapeSizeAndPosition(shapeId: string, changes: {size?: ShapeSize, position?: ShapePosition}) {
		const shape = this.getShape(shapeId)
		if (!shape) {
			throw new Error(`Shape with id ${shapeId} not found`)
		}

		if (!changes.size && !changes.position) {
			return
		}

		const newSize = changes.size ?? shape.getSize()
		const newPosition = changes.position ?? shape.getPosition()

		if (newPosition.x < 0 || newPosition.y < 0) {
			throw new Error(`Invalid shape position. X and y must not be less than 0`)
		}
		if (newSize.width <= 0 || newSize.height <= 0) {
			throw new Error(`Invalid shape size. Width and height must be greater than 0`)
		}
		if ((newSize.width + newPosition.x) > this.canvasSize.width || (newSize.height + newPosition.y) > this.canvasSize.height) {
			throw new Error(`Shape size exceeds canvas boundaries`)
		}

		shape.move(newPosition)
		shape.resize(newSize)
		this.notifyObservers(shapeId, 'update')
	}

	addObserver(onShapeChange: ShapeChangeObserver) {
		this.shapeChangeObservers.push(onShapeChange)
	}

	removeObserver(onShapeChange: ShapeChangeObserver) {
		const index = this.shapeChangeObservers.indexOf(onShapeChange)
		if (index !== -1) {
			this.shapeChangeObservers.splice(index, 1)
		}
	}

	removeShape(shapeId: string) {
		if (this.shapes.has(shapeId)) {
			this.shapes.delete(shapeId)
			this.notifyObservers(shapeId, 'delete')
		}
	}

	getShape(shapeId: string): BaseShape {
		const shape = this.shapes.get(shapeId)
		if (!shape) {
			throw new Error(`Shape with id ${shapeId} not found`)
		}
		return shape
	}

	getShapeIdToShapeMap(): Map<string, BaseShape> {
		return new Map(this.shapes)
	}

	getCanvasSize(): ShapeSize {
		return this.canvasSize
	}

	addShape(shape: BaseShape, shapeId?: string): string {
		const id = shapeId ?? Date.now().toString()
		this.shapes.set(id, shape)
		this.notifyObservers(id, 'create')
		return id
	}

	serializeCanvasToJson(): string {
		const shapes = Array.from(this.getShapeIdToShapeMap().entries()).map(([shapeId, shape]) => ({
			shapeId,
			type: shape.getType(),
			size: shape.getSize(),
			position: shape.getPosition(),
			data: (shape as any).getData?.() || undefined,
		}))

		const canvasData = {
			canvasSize: this.getCanvasSize(),
			shapes,
		}

		return JSON.stringify(canvasData)
	}

	loadCanvasFromJson(jsonString: string) {
		const jsonData = JSON.parse(jsonString)

		if (this.validateCanvasDataJson(jsonData)) {
			console.log(jsonData)
			const currentShapes = Array.from(this.getShapeIdToShapeMap().keys())
			currentShapes.forEach(shapeId => this.removeShape(shapeId))
			this.canvasSize = jsonData.canvasSize
			jsonData.shapes.forEach((shape: any) => {
				const newShape = ShapeFactory.constructShape(
					shape.type,
					shape.data,
				)
				newShape.resize(shape.size)
				newShape.move(shape.position)
				this.addShape(newShape, shape.shapeId)
			})
		}
		else {
			throw new Error('Invalid canvas data format')
		}
	}

	private validateShapeJson(shape: any): boolean {
		return (
			typeof shape.shapeId === 'string'
			&& typeof shape.type === 'string'
			&& typeof shape.size === 'object'
			&& typeof shape.size.width === 'number'
			&& typeof shape.size.height === 'number'
			&& typeof shape.position === 'object'
			&& typeof shape.position.x === 'number'
			&& typeof shape.position.y === 'number'
			&& (shape.data === undefined || typeof shape.data === 'string')
		)
	}

	private validateCanvasDataJson(data: any): boolean {
		return (
			typeof data.canvasSize === 'object'
			&& typeof data.canvasSize.width === 'number'
			&& typeof data.canvasSize.height === 'number'
			&& Array.isArray(data.shapes)
			&& data.shapes.every((shape: any) => this.validateShapeJson(shape))
		)
	}

	private notifyObservers(shapeId: string, event: ChangeEvent) {
		for (const observer of this.shapeChangeObservers) {
			observer(shapeId, event)
		}
	}
}

export {
	CanvasModel,
}

export type {
	ICanvasModel,
	ShapeChangeObserver,
	ChangeEvent,
}