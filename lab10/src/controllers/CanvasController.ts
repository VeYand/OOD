import {CanvasModel} from '../models/CanvasModel'
import {ArtObjectType} from '../types/shapes'

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

	moveShape(shapeId: string, x: number, y: number) {
		const shape = this.model.getShape(shapeId)
		shape?.move(x, y)
	}
}

export {
	CanvasController,
}