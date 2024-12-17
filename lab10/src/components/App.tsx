import {Component} from 'react'
import {CanvasController} from '../controllers/CanvasController'
import {CanvasModel} from '../models/CanvasModel'
import {Canvas} from './Canvas/Canvas'
import {Toolbar} from './Toolbar/Toolbar'

type AppProps = {}

type AppState = {
	selectedShapeId?: string,
}

class App extends Component<AppProps, AppState> {
	private readonly model: CanvasModel
	private readonly controller: CanvasController

	constructor(props: AppProps) {
		super(props)
		this.model = new CanvasModel()
		this.controller = new CanvasController(this.model)
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