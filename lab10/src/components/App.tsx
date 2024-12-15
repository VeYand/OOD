import {CanvasController} from '../controllers/CanvasController'
import {CanvasModel} from '../models/CanvasModel'
import {Canvas} from './Canvas/Canvas'
import {Toolbar} from './Toolbar/Toolbar'

const App = () => {
	const model = new CanvasModel()
	const controller = new CanvasController(model)

	return (
		<div>
			<Toolbar controller={controller}/>
			<Canvas model={model} controller={controller}/>
		</div>
	)
}

export {
	App,
}