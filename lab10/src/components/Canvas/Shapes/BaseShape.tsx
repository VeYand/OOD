import React, {Component, createRef, ReactElement} from 'react'

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
	private isDragging = false
	private dragStartX = 0
	private dragStartY = 0
	private resizeCorner = ''

	private isResizing = false
	private resizeStartX = 0
	private resizeStartY = 0
	private initialWidth = 0
	private initialHeight = 0
	private initialX = 0
	private initialY = 0

	private shapeRef = createRef<HTMLDivElement>()

	handleMouseDown = (e: React.MouseEvent) => {
		e.stopPropagation()
		this.props.setIsSelected(true)
		this.isDragging = true
		this.dragStartX = e.clientX
		this.dragStartY = e.clientY
	}

	handleMouseMove = (e: MouseEvent) => {
		if (this.isDragging) {
			const deltaX = e.clientX - this.dragStartX
			const deltaY = e.clientY - this.dragStartY
			this.props.onDrag({x: this.props.position.x + deltaX, y: this.props.position.y + deltaY})
		}

		if (this.isResizing) {
			const deltaX = e.clientX - this.resizeStartX
			const deltaY = e.clientY - this.resizeStartY

			let newWidth = this.initialWidth
			let newHeight = this.initialHeight
			let newX = this.initialX
			let newY = this.initialY

			switch (this.resizeCorner) {
				case 'top-left':
					newWidth = this.initialWidth - deltaX
					newHeight = this.initialHeight - deltaY
					newX = this.initialX + deltaX
					newY = this.initialY + deltaY
					break
				case 'top-right':
					newWidth = this.initialWidth + deltaX
					newHeight = this.initialHeight - deltaY
					newY = this.initialY + deltaY
					break
				case 'bottom-left':
					newWidth = this.initialWidth - deltaX
					newHeight = this.initialHeight + deltaY
					newX = this.initialX + deltaX
					break
				case 'bottom-right':
					newWidth = this.initialWidth + deltaX
					newHeight = this.initialHeight + deltaY
					break
				default:
					return
			}

			this.props.onResize({width: newWidth, height: newHeight})
			this.props.onDrag({x: newX, y: newY})
		}
	}

	handleMouseUp = () => {
		this.isDragging = false
		this.isResizing = false
		window.removeEventListener('mousemove', this.handleMouseMove)
		window.removeEventListener('mouseup', this.handleMouseUp)
	}

	handleResizeMouseDown = (e: React.MouseEvent, corner: string) => {
		e.stopPropagation()
		this.isResizing = true
		this.resizeCorner = corner
		this.resizeStartX = e.clientX
		this.resizeStartY = e.clientY
		this.initialWidth = this.props.size.width
		this.initialHeight = this.props.size.height
		this.initialX = this.props.position.x
		this.initialY = this.props.position.y

		window.addEventListener('mousemove', this.handleMouseMove)
		window.addEventListener('mouseup', this.handleMouseUp)
	}

	renderResizeHandles() {
		const {isSelected} = this.props
		if (!isSelected) {
			return null
		}

		return (
			<>
				<div
					style={{
						position: 'absolute',
						top: -5,
						left: -5,
						width: 10,
						height: 10,
						backgroundColor: 'red',
						cursor: 'nw-resize',
					}}
					onMouseDown={e => this.handleResizeMouseDown(e, 'top-left')}
				/>
				<div
					style={{
						position: 'absolute',
						top: -5,
						right: -5,
						width: 10,
						height: 10,
						backgroundColor: 'red',
						cursor: 'ne-resize',
					}}
					onMouseDown={e => this.handleResizeMouseDown(e, 'top-right')}
				/>
				<div
					style={{
						position: 'absolute',
						bottom: -5,
						left: -5,
						width: 10,
						height: 10,
						backgroundColor: 'red',
						cursor: 'sw-resize',
					}}
					onMouseDown={e => this.handleResizeMouseDown(e, 'bottom-left')}
				/>
				<div
					style={{
						position: 'absolute',
						bottom: -5,
						right: -5,
						width: 10,
						height: 10,
						backgroundColor: 'red',
						cursor: 'se-resize',
					}}
					onMouseDown={e => this.handleResizeMouseDown(e, 'bottom-right')}
				/>
			</>
		)
	}
	handleClickOutside = (event: MouseEvent | TouchEvent) => {
		if (this.shapeRef.current && !this.shapeRef.current.contains(event.target as Node)) {
			this.props.setIsSelected(false)
		}
	}

	override render() {
		const {isSelected, size, position, shape} = this.props

		return (
			<div
				style={{
					position: 'absolute',
					top: position.y,
					left: position.x,
					width: size.width,
					height: size.height,
					outline: isSelected ? '2px solid blue' : 'none',
					cursor: 'move',
				}}
				onMouseDown={this.handleMouseDown}
			>
				<div style={{width: '100%', height: '100%'}} ref={this.shapeRef}>{shape}</div>
				{this.renderResizeHandles()}
			</div>
		)
	}

	override componentDidMount() {
		document.addEventListener('mousedown', this.handleClickOutside)
		document.addEventListener('touchend', this.handleClickOutside)
	}

	override componentWillUnmount() {
		document.removeEventListener('mousedown', this.handleClickOutside)
		document.removeEventListener('touchend', this.handleClickOutside)
	}
}

export {BaseShape}
