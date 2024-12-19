import {CanvasModel, ShapeChangeObserver} from '../models/CanvasModel'
import {
	InsertArtObjectCommand,
	InsertImageObjectCommand,
	LoadJsonCommand,
	RemoveShapeCommand,
} from '../models/Command/commands'
import {History} from '../models/history/history'
import {ArtObjectType} from '../types/shapes'

class CanvasController {
	constructor(
		private history: History,
		private model: CanvasModel,
	) {
	}

	addArtObject(type: ArtObjectType) {
		this.history.addAndExecuteCommand(new InsertArtObjectCommand(type, this.model))
	}

	addImage(data: string) {
		this.history.addAndExecuteCommand(new InsertImageObjectCommand(data, this.model))
	}

	removeShape(shapeId: string) {
		this.history.addAndExecuteCommand(new RemoveShapeCommand(shapeId, this.model))
	}

	undo() {
		if (this.history.canUndo()) {
			this.history.undo()
		}
	}

	redo() {
		if (this.history.canRedo()) {
			this.history.redo()
		}
	}

	canUndo = () => this.history.canUndo()

	canRedo = () => this.history.canRedo()

	loadCanvasFromJson(jsonString: string) {
		this.history.addAndExecuteCommand(new LoadJsonCommand(jsonString, this.model))
	}

	addObserver(onShapeChange: ShapeChangeObserver) {
		this.model.addObserver(onShapeChange)
	}

	removeObserver(onShapeChange: ShapeChangeObserver) {
		this.model.removeObserver(onShapeChange)
	}
}

export {
	CanvasController,
}