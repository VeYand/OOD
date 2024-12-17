import {Component, ReactElement} from 'react'
import {CanvasController} from '../../controllers/CanvasController'
import {CanvasModel} from '../../models/CanvasModel'
import {ImageShape as ImageShapeModel} from '../../models/Shape/ImageShape'
import {EllipseShape} from './Shapes/EllipseShape'
import {ImageShape} from './Shapes/ImageShape'
import {InteractiveShape} from './Shapes/InteractiveShape'
import {RectangleShape} from './Shapes/RectangleShape'
import {TriangleShape} from './Shapes/TriangleShape'

type CanvasProps = {
	model: CanvasModel,
	controller: CanvasController,
}

type CanvasState = {
	selectedShapeId?: string,
}

class Canvas extends Component<CanvasProps, CanvasState> {
	private model: CanvasModel
	private controller: CanvasController

	constructor(props: CanvasProps) {
		super(props)
		this.model = props.model
		this.controller = props.controller
		this.state = {
			selectedShapeId: undefined,
		}
	}

	handleSelectShape = (shapeId?: string) => {
		this.setState({selectedShapeId: shapeId})
	}

	renderShapes = () => {
		const shapesComponents: ReactElement[] = []
		this.model.getShapeIdToShapeMap().forEach((shape, shapeId) => {
			const isSelected = this.state.selectedShapeId === shapeId
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
						this.handleSelectShape(selected ? shapeId : undefined)
					}
					size={size}
					position={position}
					shape={shapeComponent}
					onDrag={newPosition => this.controller.moveShape(shapeId, newPosition)}
					onResize={newSize => this.controller.resizeShape(shapeId, newSize)}
				/>,
			)
		})
		return shapesComponents
	}

	handleKeyDown = (event: KeyboardEvent) => {
		if (event.key === 'Delete' && this.state.selectedShapeId) {
			this.controller.removeShape(this.state.selectedShapeId)
		}
	}

	override render() {
		const canvasSize = this.model.getCanvasSize()

		return (
			<div
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
		this.model.setObserver(() => this.forceUpdate())
		document.addEventListener('keydown', this.handleKeyDown)
	}

	override componentWillUnmount() {
		document.removeEventListener('keydown', this.handleKeyDown)
	}
}

export {
	Canvas,
}
