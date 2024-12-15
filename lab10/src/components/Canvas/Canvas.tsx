import {ChangeEvent, useEffect, useRef, useState} from 'react'
import {CanvasController} from '../../controllers/CanvasController'
import {CanvasModel} from '../../models/CanvasModel'
import {BaseShape} from '../../models/Shape/BaseShape'

type CanvasProps = {
	model: CanvasModel,
	controller: CanvasController,
}

const Canvas = ({model, controller}: CanvasProps) => {
	const observer = (shapeId: string, event: ChangeEvent) => {

	}
	model.setObserver(observer)

	return <canvas width={800} height={600} style={{border: '1px solid #000'}}></canvas>
}

export {
	Canvas,
}