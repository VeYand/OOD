import {ShapePosition, ShapeSize, ShapeType} from '../../types/shapes'

abstract class BaseShape {
	private position: ShapePosition = {x: 0, y: 0}
	private size: ShapeSize

	constructor(size: ShapeSize) {
		this.size = size
	}

	getPosition(): ShapePosition {
		return this.position
	}

	getSize(): ShapeSize {
		return this.size
	}

	resize(size: ShapeSize): void {
		this.size = size
	}

	move(position: ShapePosition): void {
		this.position = position
	}

	abstract getType(): ShapeType
}

export {
	BaseShape,
}
