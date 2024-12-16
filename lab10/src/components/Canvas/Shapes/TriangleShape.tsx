import {Component} from 'react'

type TriangleShapeProps = {}

class TriangleShape extends Component<TriangleShapeProps> {
	override render() {
		return (
			<svg width="100%" height="100%">
				<polygon points="50,0 100,100 0,100" fill="red" />
			</svg>
		)
	}
}

export {
	TriangleShape,
}