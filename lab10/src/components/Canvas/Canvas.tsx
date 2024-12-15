import {useEffect, useRef, useState} from 'react'
import {CanvasController} from '../../controllers/CanvasController'
import {CanvasModel} from '../../models/CanvasModel'
import {BaseShape} from '../../models/Shape/BaseShape'

type CanvasProps = {
	model: CanvasModel,
	controller: CanvasController,
}

const Canvas = ({model, controller}: CanvasProps) => {
	const [shapes, setShapes] = useState<BaseShape[]>(model.getShapes())


	model.addObserver(setShapes)
	const canvasRef = useRef<HTMLCanvasElement>(null)

	useEffect(() => {
		const canvas = canvasRef.current
		if (canvas) {
			const ctx = canvas.getContext('2d')
			if (ctx) {
				model.getShapes().forEach(shape => shape.draw(ctx))
			}
		}
	}, [controller, model])

	return <canvas ref={canvasRef} width={800} height={600} style={{border: '1px solid #000'}}></canvas>
}

export {
	Canvas,
}