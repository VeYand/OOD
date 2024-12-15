import {ArtObjectType, ShapePosition, ShapeSize} from '../types/shapes'
import {BaseShape} from './Shape/BaseShape'
import {ShapeFactory} from './ShapeFactory'

type ChangeEvent = 'create' | 'update' | 'delete'

type ShapeChangeObserver = (shapeId: string, event: ChangeEvent) => void

class CanvasModel {
	private shapes: Map<string, BaseShape> = new Map()
	private shapeChangeObserver?: ShapeChangeObserver

	addArtObject(type: ArtObjectType): void {
		this.addShape(ShapeFactory.constructShape(type))
	}

	addImage(data: string) {
		this.addShape(ShapeFactory.constructShape('image', data))
	}

	resizeShape(shapeId: string, size: ShapeSize) {
		this.getShape(shapeId)?.resize(size)
	}

	moveShape(shapeId: string, position: ShapePosition) {
		this.getShape(shapeId)?.move(position)
	}

	setObserver(onShapeChange: ShapeChangeObserver) {
		this.shapeChangeObserver = onShapeChange
	}

	removeShape(shapeId: string) {
		this.shapes.delete(shapeId)
		this.shapeChangeObserver?.(shapeId, 'delete')
	}

	getShape(shapeId: string): BaseShape | undefined {
		return this.shapes.get(shapeId)
	}

	getShapes(): BaseShape[] {
		return [...this.shapes.values()]
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
}