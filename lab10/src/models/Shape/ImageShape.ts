import {BaseShape} from './BaseShape'

class ImageShape extends BaseShape {
	data: string

	constructor(width: number, height: number, data: string) {
		super(width, height)
		this.data = data
	}

	draw(ctx: CanvasRenderingContext2D): void {
		ctx.ellipse(1, 1, 1, 1, 1, 1, 1)
	}
}

export {
	ImageShape,
}