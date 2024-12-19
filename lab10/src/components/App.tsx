import {Component} from 'react'
import {CanvasController} from '../controllers/CanvasController'
import {ICanvasModel} from '../models/CanvasModel'
import {Canvas} from './Canvas/Canvas'
import {Toolbar} from './Toolbar/Toolbar'

type AppProps = {
	model: ICanvasModel,
	controller: CanvasController,
}

type AppState = {
	model: ICanvasModel,
	controller: CanvasController,
	selectedShapeId?: string,
}

class App extends Component<AppProps, AppState> {
	constructor(props: AppProps) {
		super(props)
		this.state = {
			model: this.props.model,
			controller: this.props.controller,
		}
	}

	handleSelectShape = (shapeId?: string) => {
		this.setState({selectedShapeId: shapeId})
	}

	handleDeleteShape = (shapeId: string) => {
		this.state.controller.removeShape(shapeId)
	}

	override render() {
		return (
			<div style={{display: 'flex'}}>
				<div style={{margin: '0 auto'}}>
					<Toolbar
						controller={this.state.controller}
						selectedShapeId={this.state.selectedShapeId}
						handleDeleteShape={this.handleDeleteShape}
					/>
					<Canvas
						model={this.state.model}
						controller={this.state.controller}
						handleSelectShape={this.handleSelectShape}
						selectedShapeId={this.state.selectedShapeId}
						handleDeleteShape={this.handleDeleteShape}
					/>
				</div>
			</div>
		)
	}
}

export {
	App,
}