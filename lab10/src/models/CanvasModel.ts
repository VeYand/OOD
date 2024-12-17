import {ArtObjectType, ShapePosition, ShapeSize} from '../types/shapes'
import {BaseShape} from './Shape/BaseShape'
import {ShapeFactory} from './ShapeFactory'

type ChangeEvent = 'create' | 'update' | 'delete'

type ShapeChangeObserver = (shapeId: string, event: ChangeEvent) => void

class CanvasModel {
	private canvasSize: ShapeSize = {width: 800, height: 600}
	private shapes: Map<string, BaseShape> = new Map()
	private shapeChangeObserver?: ShapeChangeObserver

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
		this.shapeChangeObserver?.(shapeId, 'update')
	}

	setObserver(onShapeChange: ShapeChangeObserver) {
		this.shapeChangeObserver = onShapeChange
	}

	removeShape(shapeId: string) {
		if (!this.shapes.has(shapeId)) {
			throw new Error(`Shape with id ${shapeId} not found`)
		}
		this.shapes.delete(shapeId)
		this.shapeChangeObserver?.(shapeId, 'delete')
	}

	getShape(shapeId: string): BaseShape | undefined {
		return this.shapes.get(shapeId)
	}

	getShapeIdToShapeMap(): Map<string, BaseShape> {
		return this.shapes
	}

	getCanvasSize(): ShapeSize {
		return this.canvasSize
	}

	private addShape(shape: BaseShape): void {
		const shapeId = Date.now().toString()
		this.shapes.set(shapeId, shape)
		this.shapeChangeObserver?.(shapeId, 'create')
	}
}

export {
	CanvasModel,
}

export type {
	ShapeChangeObserver,
	ChangeEvent,
}