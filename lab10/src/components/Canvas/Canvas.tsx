import {Component, ReactElement} from 'react'
import {CanvasController} from '../../controllers/CanvasController'
import {ShapeController} from '../../controllers/ShapeController'
import {ChangeEvent, ICanvasReadModel} from '../../models/CanvasModel'
import {IShape} from '../../models/Shape/BaseShape'
import {ImageShape as ImageShapeModel} from '../../models/Shape/ImageShape'
import {EllipseShape} from './Shapes/EllipseShape'
import {ImageShape} from './Shapes/ImageShape'
import {InteractiveShape} from './Shapes/InteractiveShape'
import {RectangleShape} from './Shapes/RectangleShape'
import {TriangleShape} from './Shapes/TriangleShape'

type CanvasProps = {
	model: ICanvasReadModel,
	canvasController: CanvasController,
	shapeController: ShapeController,
	selectedShapeId?: string,
	handleSelectShape: (shapeId?: string) => void,
	handleDeleteShape: (shapeId: string) => void,
}

type CanvasState = {
	shapes: ReactElement[],
}

class Canvas extends Component<CanvasProps, CanvasState> {
	private model: ICanvasReadModel
	private canvasController: CanvasController
	private shapeController: ShapeController

	constructor(props: CanvasProps) {
		super(props)
		this.model = props.model
		this.canvasController = props.canvasController
		this.shapeController = this.props.shapeController
		this.state = {
			shapes: this.renderShapes(),
		}
	}


	renderShape(shapeId: string, shape: IShape, isSelected: boolean): ReactElement {
		const position = shape.getPosition()
		const size = shape.getSize()

		let shapeComponent: ReactElement = <></>
		switch (shape.getType()) {
			case 'ellipse':
				shapeComponent = <EllipseShape />
				break
			case 'rectangle':
				shapeComponent = <RectangleShape />
				break
			case 'triangle':
				shapeComponent = <TriangleShape />
				break
			case 'image':
				if (shape instanceof ImageShapeModel) {
					shapeComponent = <ImageShape src={shape.getData()}/>
				}
				break
		}

		return (
			<InteractiveShape
				key={shapeId}
				isSelected={isSelected}
				setIsSelected={selected => {
					this.props.handleSelectShape(selected ? shapeId : undefined)
					this.setState(prevState => ({
						shapes: prevState.shapes.map(prevShape =>
							(prevShape.key === shapeId
								? this.renderShape(shapeId, this.model.getShape(shapeId), selected)
								: this.renderShape(prevShape.key ?? '', this.model.getShape(prevShape.key ?? ''), false)),
						),
					}))
				}}
				shapeSize={size}
				shapePosition={position}
				shape={shapeComponent}
				canvasSize={this.model.getCanvasSize()}
				shapeId={shapeId}
				shapeController={this.shapeController}
			/>
		)
	}

	renderShapes = () => {
		const shapesComponents: ReactElement[] = []
		this.model.getShapeIdToShapeMap().forEach((shape, shapeId) => {
			shapesComponents.push(this.renderShape(shapeId, shape, this.props.selectedShapeId === shapeId))
		})
		return shapesComponents
	}

	handleKeyDown = (event: KeyboardEvent) => {
		if (event.key === 'Delete' && this.props.selectedShapeId) {
			this.props.handleDeleteShape(this.props.selectedShapeId)
		}
	}

	override render() {
		const canvasSize = this.model.getCanvasSize()

		return (
			<div
				id={'canvas'}
				style={{
					position: 'relative',
					width: canvasSize.width,
					height: canvasSize.height,
					backgroundColor: '#f0f0f0',
					overflow: 'hidden',
				}}
			>
				{this.state.shapes}
			</div>
		)
	}

	override componentDidMount() {
		this.canvasController.addObserver((shapeId: string, event: ChangeEvent) => {
			switch (event) {
				case 'create':
					this.setState(prevState => ({
						shapes: [...prevState.shapes, this.renderShape(shapeId, this.model.getShape(shapeId), this.props.selectedShapeId === shapeId)],
					}))
					break
				case 'delete':
					this.setState(prevState => ({
						shapes: prevState.shapes.filter(shape => shape.key !== shapeId),
					}))
					break
				case 'update':
					this.setState(prevState => ({
						shapes: prevState.shapes.map(shape =>
							(shape.key === shapeId ? this.renderShape(shapeId, this.model.getShape(shapeId), this.props.selectedShapeId === shapeId) : shape),
						),
					}))
					break
			}
		})

		document.addEventListener('keydown', this.handleKeyDown)
	}

	override componentWillUnmount() {
		document.removeEventListener('keydown', this.handleKeyDown)
	}
}

export {
	Canvas,
}
