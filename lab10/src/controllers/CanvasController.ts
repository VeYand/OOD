import {CanvasModel, ShapeChangeObserver} from '../models/CanvasModel'
import {ArtObjectType, ShapePosition, ShapeSize} from '../types/shapes'

class CanvasController {
	constructor(private model: CanvasModel) {}

	addArtObject(type: ArtObjectType) {
		this.model.addArtObject(type)
	}

	addImage(data: string) {
		this.model.addImage(data)
	}

	removeShape(shapeId: string) {
		this.model.removeShape(shapeId)
	}

	updateShapeSizeAndPosition(shapeId: string, changes: {size?: ShapeSize, position?: ShapePosition}) {
		this.model.updateShapeSizeAndPosition(shapeId, changes)
	}

	setObserver(onShapeChange: ShapeChangeObserver) {
		this.model.setObserver(onShapeChange)
	}
}

export {
	CanvasController,
}