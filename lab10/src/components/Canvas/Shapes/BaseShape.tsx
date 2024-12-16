import React, {Component, ReactElement} from 'react'

type BaseShapeProps = {
	isSelected: boolean,
	setIsSelected: (selected: boolean) => void,
	size: {width: number, height: number},
	position: {x: number, y: number},
	shape: ReactElement,
	onDrag: (position: {x: number, y: number}) => void,
	onResize: (size: {width: number, height: number}) => void,
}

class BaseShape extends Component<BaseShapeProps> {
	handleMouseDown = (e: React.MouseEvent) => {
		e.stopPropagation()
		this.props.setIsSelected(true)
	}

	override render() {
		const {isSelected, size, position, shape, onDrag, onResize} = this.props

		return (
			<div
				style={{
					position: 'absolute',
					top: position.y,
					left: position.x,
					width: size.width,
					height: size.height,
					border: isSelected ? '2px solid blue' : 'none',
					cursor: 'move',
				}}
				onMouseDown={this.handleMouseDown}
				draggable
				onDrag={e =>
					onDrag({
						x: position.x + e.movementX,
						y: position.y + e.movementY,
					})
				}
			>
				{shape}
				{isSelected && (
					<div
						style={{
							position: 'absolute',
							bottom: 0,
							right: 0,
							width: 10,
							height: 10,
							backgroundColor: 'red',
							cursor: 'se-resize',
						}}
						onMouseDown={e => e.stopPropagation()}
						onDrag={e =>
							onResize({
								width: size.width + e.movementX,
								height: size.height + e.movementY,
							})
						}
					/>
				)}
			</div>
		)
	}
}

export {BaseShape}
