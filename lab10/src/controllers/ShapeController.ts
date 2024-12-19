import {CanvasModel} from '../models/CanvasModel'
import {ShapePosition, ShapeSize} from '../types/shapes'

class ShapeController {
	constructor(private model: CanvasModel) {}

	updateShapeSizeAndPosition(shapeId: string, changes: {size?: ShapeSize, position?: ShapePosition}) {
		this.model.updateShapeSizeAndPosition(shapeId, changes)
	}

	handleDrag(shapeId: string, deltaX: number, deltaY: number) {
		const shape = this.model.getShape(shapeId)
		if (!shape) {
			return
		}

		const newPosition: ShapePosition = {
			x: Math.max(0, Math.min(shape.getPosition().x + deltaX, this.model.getCanvasSize().width - shape.getSize().width)),
			y: Math.max(0, Math.min(shape.getPosition().y + deltaY, this.model.getCanvasSize().height - shape.getSize().height)),
		}
		this.updateShapeSizeAndPosition(shapeId, {position: newPosition})
	}

	handleResize(shapeId: string, corner: string, deltaX: number, deltaY: number) {
		const shape = this.model.getShape(shapeId)
		if (!shape) {
			return
		}

		let {x, y, width, height} = {...shape.getPosition(), ...shape.getSize()}
		const minSize = 20

		switch (corner) {
			case 'top-left':
				width = Math.max(minSize, width - deltaX)
				height = Math.max(minSize, height - deltaY)
				x += deltaX
				y += deltaY
				break
			case 'top-right':
				width = Math.max(minSize, width + deltaX)
				height = Math.max(minSize, height - deltaY)
				y += deltaY
				break
			case 'bottom-left':
				width = Math.max(minSize, width - deltaX)
				height = Math.max(minSize, height + deltaY)
				x += deltaX
				break
			case 'bottom-right':
				width = Math.max(minSize, width + deltaX)
				height = Math.max(minSize, height + deltaY)
				break
		}

		x = Math.max(0, x)
		y = Math.max(0, y)
		width = Math.min(width, this.model.getCanvasSize().width - x)
		height = Math.min(height, this.model.getCanvasSize().height - y)

		this.updateShapeSizeAndPosition(shapeId, {size: {width, height}, position: {x, y}})
	}
}

export {ShapeController}
