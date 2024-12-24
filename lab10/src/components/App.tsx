import {Component} from 'react'
import {CanvasController} from '../controllers/CanvasController'
import {ShapeController} from '../controllers/ShapeController'
import {ICanvasReadModel} from '../models/CanvasModel'
import {Canvas} from './Canvas/Canvas'
import {Toolbar} from './Toolbar/Toolbar'

type AppProps = {
	model: ICanvasReadModel,
	canvasController: CanvasController,
	shapeController: ShapeController,
}

type AppState = {
	model: ICanvasReadModel,
	canvasController: CanvasController,
	shapeController: ShapeController,
	selectedShapeIds: string[],
}

class App extends Component<AppProps, AppState> {
	constructor(props: AppProps) {
		super(props)
		this.state = {
			model: this.props.model,
			canvasController: this.props.canvasController,
			shapeController: this.props.shapeController,
			selectedShapeIds: [],
		}
	}

	setSelectedShapes = (shapeIds: string[]) => {
		this.setState({selectedShapeIds: shapeIds})
	}

	handleDeleteShapes = (shapeIds: string[]) => {
		for (const shapeId of shapeIds) {
			this.state.canvasController.removeShape(shapeId)
		}
	}

	override render() {
		return (
			<div style={{display: 'flex'}}>
				<div style={{margin: '0 auto'}}>
					<Toolbar
						canvasModel={this.state.model}
						controller={this.state.canvasController}
						selectedShapeIds={this.state.selectedShapeIds}
						setSelectedShapeIds={this.setSelectedShapes}
						handleDeleteShapes={this.handleDeleteShapes}
					/>
					<Canvas
						model={this.state.model}
						canvasController={this.state.canvasController}
						shapeController={this.state.shapeController}
						setSelectedShapeIds={this.setSelectedShapes}
						selectedShapeIds={this.state.selectedShapeIds}
						handleDeleteShapes={this.handleDeleteShapes}
					/>
				</div>
			</div>
		)
	}
}

export {
	App,
}