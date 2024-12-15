import {CanvasModel} from '../models/CanvasModel'
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

	resizeShape(shapeId: string, size: ShapeSize) {
		this.model.resizeShape(shapeId, size)
	}

	moveShape(shapeId: string, position: ShapePosition) {
		this.model.moveShape(shapeId, position)
	}
}

export {
	CanvasController,
}