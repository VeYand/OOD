import {Component} from 'react'

type ImageShapeProps = {
	src: string,
}

class ImageShape extends Component<ImageShapeProps> {
	override render() {
		const {src} = this.props
		return (
			<svg width="100%" height="100%">
				<image href={src} width="100%" height="100%" />
			</svg>
		)
	}
}

export {
	ImageShape,
}