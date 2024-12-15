import {BaseShape} from './BaseShape'

class Rectangle extends BaseShape {
	draw(ctx: CanvasRenderingContext2D): void {
		ctx.ellipse(1, 1, 1, 1, 1, 1, 1)
	}
}

export {
	Rectangle,
}