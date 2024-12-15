import {ArtObjectType} from '../types/shapes'
import {BaseShape} from './Shape/BaseShape'
import {Ellipse} from './Shape/Ellipse'
import {ImageShape} from './Shape/ImageShape'
import {Rectangle} from './Shape/Rectangle'
import {Triangle} from './Shape/Triangle'

type ChangeEvent = 'create' | 'update' | 'delete'

type ShapeChangeObserver = (shapeId: string, event: ChangeEvent) => void

class CanvasModel {
	private shapes: Map<string, BaseShape> = new Map()
	private shapeChangeObserver?: ShapeChangeObserver

	addArtObject(type: ArtObjectType): void {
		let shape: BaseShape
		switch (type) {
			case 'ellipse':
				shape = new Ellipse(100, 100)
				break
			case 'rectangle':
				shape = new Rectangle(100, 100)
				break
			case 'triangle':
				shape = new Triangle(100, 100)
				break
		}
		this.addShape(shape)
	}

	addImage(data: string) {
		this.addShape(new ImageShape(100, 100, data))
	}

	addObserver(onShapeChange: ShapeChangeObserver) {
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