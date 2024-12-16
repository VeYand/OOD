import React, {useCallback, useEffect, useRef} from 'react'
import {CanvasController} from '../../controllers/CanvasController'
import {CanvasModel} from '../../models/CanvasModel'
import {ShapePosition} from '../../types/shapes'

type CanvasProps = {
	model: CanvasModel,
	controller: CanvasController,
}

const Canvas = ({model, controller}: CanvasProps) => {
	const canvasRef = useRef<HTMLCanvasElement>(null)
	const selectedShapeIdRef = useRef<string | null>(null)
	const offsetRef = useRef<ShapePosition>({x: 0, y: 0})

	const drawShapes = useCallback(() => {
		const canvas = canvasRef.current
		const ctx = canvas?.getContext('2d')
		if (!canvas || !ctx) {
			return
		}

		ctx.clearRect(0, 0, canvas.width, canvas.height) // Clear canvas

		model.getShapeIdToShapeMap().forEach(shape => {
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
					ctx.moveTo(position.x, position.y)
					ctx.lineTo(position.x + size.width, position.y)
					ctx.lineTo(position.x + size.width / 2, position.y - size.height)
					ctx.closePath()
					break
				case 'image':
					break
				default:
					break
			}
			ctx.stroke()
		})
	}, [model])

	useEffect(() => {
		const observer = () => {
			drawShapes()
		}

		model.setObserver(observer)
		drawShapes()

		return () => model.setObserver(() => {})
	}, [drawShapes, model])


	const handleMouseDown = (event: React.MouseEvent<HTMLCanvasElement>) => {
		const canvas = canvasRef.current
		if (!canvas) {
			return
		}

		const rect = canvas.getBoundingClientRect()
		const mousePos = {
			x: event.clientX - rect.left,
			y: event.clientY - rect.top,
		}

		for (const [shapeId, shape] of model.getShapeIdToShapeMap()) {
			const position = shape.getPosition()
			const size = shape.getSize()
			if (
				mousePos.x >= position.x
				&& mousePos.x <= position.x + size.width
				&& mousePos.y >= position.y
				&& mousePos.y <= position.y + size.height
			) {
				selectedShapeIdRef.current = shapeId
				offsetRef.current = {
					x: mousePos.x - position.x,
					y: mousePos.y - position.y,
				}
			}
		}
	}

	const handleMouseMove = (event: React.MouseEvent<HTMLCanvasElement>) => {
		const canvas = canvasRef.current
		if (!canvas || !selectedShapeIdRef.current) {
			return
		}

		const rect = canvas.getBoundingClientRect()
		const mousePos = {
			x: event.clientX - rect.left,
			y: event.clientY - rect.top,
		}

		const newPosition = {
			x: mousePos.x - offsetRef.current.x,
			y: mousePos.y - offsetRef.current.y,
		}

		controller.moveShape(selectedShapeIdRef.current, newPosition)
	}

	const handleMouseUp = () => {
		selectedShapeIdRef.current = null
	}

	return (
		<canvas
			ref={canvasRef}
			width={800}
			height={600}
			style={{border: '1px solid #000'}}
			onMouseDown={handleMouseDown}
			onMouseMove={handleMouseMove}
			onMouseUp={handleMouseUp}
		/>
	)
}

export {
	Canvas,
}