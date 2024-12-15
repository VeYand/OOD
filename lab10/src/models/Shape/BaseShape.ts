abstract class BaseShape {
	x = 0
	y = 0
	width: number
	height: number

	constructor(width: number, height: number) {
		this.width = width
		this.height = height
	}

	resize(width: number, height: number): void {
		this.width = width
		this.height = height
	}

	move(x: number, y: number): void {
		this.x = x
		this.y = y
	}

	abstract draw(ctx: CanvasRenderingContext2D): void
}

export {
	BaseShape,
}
