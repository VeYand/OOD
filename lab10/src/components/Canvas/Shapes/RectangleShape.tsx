import {Component} from 'react'

type RectangleShapeProps = {}

class RectangleShape extends Component<RectangleShapeProps> {
	override render() {
		return (
			<svg width="100%" height="100%">
				<rect width="100%" height="100%" fill="green" />
			</svg>
		)
	}
}

export {
	RectangleShape,
}