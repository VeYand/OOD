import {Component} from 'react'
import {CanvasController} from '../controllers/CanvasController'
import {CanvasModel} from '../models/CanvasModel'
import {Canvas} from './Canvas/Canvas'
import {Toolbar} from './Toolbar/Toolbar'

type AppProps = {}

class App extends Component<AppProps> {
	private readonly model: CanvasModel
	private readonly controller: CanvasController

	constructor(props: AppProps) {
		super(props)
		this.model = new CanvasModel()
		this.controller = new CanvasController(this.model)
	}

	override render() {
		return (
			<div>
				<Toolbar controller={this.controller}/>
				<Canvas model={this.model} controller={this.controller}/>
			</div>
		)
	}
}

export {
	App,
}