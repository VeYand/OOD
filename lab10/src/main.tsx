import {createRoot} from 'react-dom/client'
import {App} from './components/App'
import {CanvasController} from './controllers/CanvasController'
import {ShapeController} from './controllers/ShapeController'
import {CanvasModel} from './models/CanvasModel'
import {History} from './models/history/history'

const root = document.getElementById('root')

const model = new CanvasModel()
const history = new History()
if (root) {
	createRoot(root).render(
		<>
			<App model={model} canvasController={new CanvasController(history, model)} shapeController={new ShapeController(history, model)}/>,
			<App model={model} canvasController={new CanvasController(history, model)} shapeController={new ShapeController(history, model)}/>,
		</>,
	)
}

//todo маркеры выделения и рамка на верхенм слое, поверх всех фигур
//todo фигура привязана к курсору
//todo фигуру можно выделить только за внутреннюю область
