import {Component} from 'react'
import {CanvasController} from '../controllers/CanvasController'
import {CanvasModel, ICanvasModel} from '../models/CanvasModel'
import {Canvas} from './Canvas/Canvas'
import {Toolbar} from './Toolbar/Toolbar'

type AppProps = {}

type AppState = {
	selectedShapeId?: string,
}

class App extends Component<AppProps, AppState> {
	private readonly model: ICanvasModel
	private readonly controller: CanvasController

	constructor(props: AppProps) {
		super(props)
		const model = new CanvasModel()
		this.model = model
		this.controller = new CanvasController(model)
		this.state = {}
	}

	handleSelectShape = (shapeId?: string) => {
		this.setState({selectedShapeId: shapeId})
	}

	handleDeleteShape = (shapeId: string) => {
		this.controller.removeShape(shapeId)
	}

	override render() {
		return (
			<div>
				<Toolbar
					controller={this.controller}
					selectedShapeId={this.state.selectedShapeId}
					handleDeleteShape={this.handleDeleteShape}
				/>
				<Canvas
					model={this.model}
					controller={this.controller}
					handleSelectShape={this.handleSelectShape}
					selectedShapeId={this.state.selectedShapeId}
					handleDeleteShape={this.handleDeleteShape}
				/>
			</div>
		)
	}
}

export {
	App,
}