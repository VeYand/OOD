import {createRoot} from 'react-dom/client'
import {App} from './components/App'
import {CanvasController} from './controllers/CanvasController'
import {CanvasModel} from './models/CanvasModel'

const root = document.getElementById('root')

const model = new CanvasModel()
if (root) {
	createRoot(root).render(
		<>
			<App model={model} controller={new CanvasController(model)}/>,
			<App model={model} controller={new CanvasController(model)}/>,
		</>,
	)
}

//todo маркеры выделения и рамка на верхенм слое, поверх всех фигур
//todo фигура привязана к курсору
//todo фигуру можно выделить только за внутреннюю область

//todo не отдавать внутренние струкутры данных наружу

// todo можно разделить контроллер наhape
