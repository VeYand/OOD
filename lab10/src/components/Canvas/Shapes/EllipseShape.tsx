import {Component} from 'react'

class EllipseShape extends Component {
	override render() {
		return (
			<svg width="100%" height="100%">
				<ellipse cx="50%" cy="50%" rx="40%" ry="30%" fill="blue" />
			</svg>
		)
	}
}

export {EllipseShape}
