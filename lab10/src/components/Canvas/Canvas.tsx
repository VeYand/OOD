import React, {Component} from 'react'
import {CanvasController} from '../../controllers/CanvasController'
import {CanvasModel} from '../../models/CanvasModel'
import {ShapePosition} from '../../types/shapes'

type CanvasProps = {
	model: CanvasModel,
	controller: CanvasController,
}

class Canvas extends Component<CanvasProps> {
	private model: CanvasModel
	private controller: CanvasController
	private readonly canvasRef: React.RefObject<HTMLCanvasElement>
	private selectedShapeIdRef: string | null
	private offsetRef: ShapePosition

	constructor(props: CanvasProps) {
		super(props)
		this.model = props.model
		this.controller = props.controller
		this.canvasRef = React.createRef<HTMLCanvasElement>()
		this.selectedShapeIdRef = null
		this.offsetRef = {x: 0, y: 0}
	}

	override render() {
		return (
			<canvas
				ref={this.canvasRef}
				width={800}
				height={600}
				style={{border: '1px solid #000'}}
				onMouseDown={event => this.handleMouseDown(event)}
				onMouseMove={event => this.handleMouseMove(event)}
				onMouseUp={() => this.handleMouseUp()}
			/>
		)
	}

	override componentDidMount() {
		const observer = () => {
			this.drawShapes()
		}

		this.model.setObserver(observer)
		this.drawShapes()
	}

	private handleMouseDown(event: React.MouseEvent<HTMLCanvasElement>) {
		const canvas = this.canvasRef.current
		if (!canvas) {
			return
		}

		const rect = canvas.getBoundingClientRect()
		const mousePos = {
			x: event.clientX - rect.left,
			y: event.clientY - rect.top,
		}

		for (const [shapeId, shape] of this.model.getShapeIdToShapeMap()) {
			const position = shape.getPosition()
			const size = shape.getSize()
			if (
				mousePos.x >= position.x
				&& mousePos.x <= position.x + size.width
				&& mousePos.y >= position.y
				&& mousePos.y <= position.y + size.height
			) {
				this.selectedShapeIdRef = shapeId
				this.offsetRef = {
					x: mousePos.x - position.x,
					y: mousePos.y - position.y,
				}
			}
		}
	}

	private handleMouseMove(event: React.MouseEvent<HTMLCanvasElement>) {
		const canvas = this.canvasRef.current
		if (!canvas || !this.selectedShapeIdRef) {
			return
		}

		const rect = canvas.getBoundingClientRect()
		const mousePos = {
			x: event.clientX - rect.left,
			y: event.clientY - rect.top,
		}

		const newPosition = {
			x: mousePos.x - this.offsetRef.x,
			y: mousePos.y - this.offsetRef.y,
		}

		this.controller.moveShape(this.selectedShapeIdRef, newPosition)
	}

	private handleMouseUp() {
		this.selectedShapeIdRef = null
	}

	private drawShapes = () => {
		const canvas = this.canvasRef.current
		if (!canvas) {
			return
		}
		const shapes = [...this.model.getShapeIdToShapeMap().values()]
		const ctx = canvas?.getContext('2d')
		if (!canvas || !ctx) {
			return
		}

		ctx.clearRect(0, 0, canvas.width, canvas.height) // Clear canvas

		shapes.forEach(shape => {
			const position = shape.getPosition()
			const size = shape.getSize()

			ctx.beginPath()
			switch (shape.getType()) {
				case 'rectangle':
					ctx.rect(position.x, position.y, size.width, size.height)
					break
				case 'ellipse':
					ctx.ellipse(
						position.x + size.width / 2,
						position.y + size.height / 2,
						size.width / 2,
						size.height / 2,
						0,
						0,
						Math.PI * 2,
					)
					break
				case 'triangle':
					ctx.moveTo(position.x, position.y + size.height)
					ctx.lineTo(position.x + size.width, position.y + size.height)
					ctx.lineTo(position.x + size.width / 2, position.y)
					ctx.closePath()
					break
				case 'image':
					break
				default:
					break
			}
			ctx.stroke()
		})
	}
}

export {Canvas}