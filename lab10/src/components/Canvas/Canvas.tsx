import {Component, ReactElement} from 'react'
import {CanvasController} from '../../controllers/CanvasController'
import {ICanvasModel} from '../../models/CanvasModel'
import {ImageShape as ImageShapeModel} from '../../models/Shape/ImageShape'
import {ShapePosition, ShapeSize} from '../../types/shapes'
import {EllipseShape} from './Shapes/EllipseShape'
import {ImageShape} from './Shapes/ImageShape'
import {InteractiveShape} from './Shapes/InteractiveShape'
import {RectangleShape} from './Shapes/RectangleShape'
import {TriangleShape} from './Shapes/TriangleShape'

type CanvasProps = {
	model: ICanvasModel,
	controller: CanvasController,
	selectedShapeId?: string,
	handleSelectShape: (shapeId?: string) => void,
	handleDeleteShape: (shapeId: string) => void,
}

class Canvas extends Component<CanvasProps> {
	private model: ICanvasModel
	private controller: CanvasController

	constructor(props: CanvasProps) {
		super(props)
		this.model = props.model
		this.controller = props.controller
	}


	renderShapes = () => {
		const shapesComponents: ReactElement[] = []
		this.model.getShapeIdToShapeMap().forEach((shape, shapeId) => {
			const isSelected = this.props.selectedShapeId === shapeId
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
				default:
					return
			}

			shapesComponents.push(
				<InteractiveShape
					key={shapeId}
					isSelected={isSelected}
					setIsSelected={selected =>
						this.props.handleSelectShape(selected ? shapeId : undefined)
					}
					shapeSize={size}
					shapePosition={position}
					shape={shapeComponent}
					updateShapeSizeAndPosition={(newSize?: ShapeSize, newPosition?: ShapePosition) =>
						this.controller.updateShapeSizeAndPosition(shapeId, {size: newSize, position: newPosition})}
					canvasSize={this.model.getCanvasSize()}
				/>,
			)
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
				{this.renderShapes()}
			</div>
		)
	}

	override componentDidMount() {
		this.controller.addObserver(() => this.forceUpdate())
		document.addEventListener('keydown', this.handleKeyDown)
	}

	override componentWillUnmount() {
		document.removeEventListener('keydown', this.handleKeyDown)
	}
}

export {
	Canvas,
}
