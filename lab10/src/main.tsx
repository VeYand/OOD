import {createRoot} from 'react-dom/client'
import {App} from './components/App'
import {CanvasController} from './controllers/CanvasController'
import {ShapeController} from './controllers/ShapeController'
import {CanvasModel} from './models/CanvasModel'

const root = document.getElementById('root')

const model = new CanvasModel()
if (root) {
	createRoot(root).render(
		<>
			<App model={model} canvasController={new CanvasController(model)} shapeController={new ShapeController(model)}/>,
			<App model={model} canvasController={new CanvasController(model)} shapeController={new ShapeController(model)}/>,
		</>,
	)
}

//todo маркеры выделения и рамка на верхенм слое, поверх всех фигур
//todo фигура привязана к курсору
//todo фигуру можно выделить только за внутреннюю область

//todo не отдавать внутренние струкутры данных наружу

// todo можно разделить контроллер наhape
