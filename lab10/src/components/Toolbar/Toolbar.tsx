import {ChangeEvent, Component} from 'react'
import {CanvasController} from '../../controllers/CanvasController'
import {ArtObjectType} from '../../types/shapes'
import {EllipseShape} from '../Canvas/Shapes/EllipseShape'
import {RectangleShape} from '../Canvas/Shapes/RectangleShape'
import {TriangleShape} from '../Canvas/Shapes/TriangleShape'

type ToolbarProps = {
	controller: CanvasController,
}

class Toolbar extends Component<ToolbarProps> {
	private controller: CanvasController

	constructor(props: ToolbarProps) {
		super(props)
		this.controller = props.controller
	}

	override render = () => (
		<div style={{display: 'flex', gap: '10px'}}>
			{this.renderCreateArtObjectBlock()}
			{this.renderImageImportBlock()}
			{this.renderJsonBlock()}
		</div>
	)

	private renderCreateArtObjectBlock(): JSX.Element {
		const onCreateArt = (type: ArtObjectType) => {
			this.controller.addArtObject(type)
		}

		return (
			<div style={{display: 'flex', gap: '10px', padding: '10px', background: '#e0e0e0', borderRadius: '5px'}}>
				<button onClick={() => onCreateArt('rectangle')}>{this.renderIcon('rectangle')}{' Rectangle'}</button>
				<button onClick={() => onCreateArt('triangle')}>{this.renderIcon('triangle')}{' Triangle'}</button>
				<button onClick={() => onCreateArt('ellipse')}>{this.renderIcon('ellipse')}{' Ellipse'}</button>
			</div>
		)
	}

	private renderIcon(type: ArtObjectType): JSX.Element {
		switch (type) {
			case 'rectangle':
				return <div style={{width: 16, height:16}}><RectangleShape/></div>
			case 'triangle':
				return <div style={{width: 16, height:16}}><TriangleShape/></div>
			case 'ellipse':
				return <div style={{width: 16, height:16}}><EllipseShape/></div>
			default:
				return <></>
		}
	}

	private renderJsonBlock(): JSX.Element {
		return (
			<div style={{display: 'flex', gap: '10px', padding: '10px', background: '#e0e0e0', borderRadius: '5px'}}>
				<button onClick={() => {}}>{'Save JSON'}</button>
				<button onClick={() => {}}>{'Load JSON'}</button>
			</div>
		)
	}

	private renderImageImportBlock(): JSX.Element {
		const handleImageUpload = (event: ChangeEvent<HTMLInputElement>) => {
			const file = event.target.files?.[0]
			if (!file) {
				return
			}

			const reader = new FileReader()
			reader.onload = e => {
				this.controller.addImage((e.target?.result ?? '') as string)
			}
			reader.readAsDataURL(file)
		}

		return (
			<div style={{display: 'flex', padding: '10px', background: '#e0e0e0', borderRadius: '5px'}}>
				<input
					id="input-image-from-pc"
					type="file"
					accept=".jpeg, .jpg, .png"
					onChange={handleImageUpload}
					style={{display: 'none'}}
				/>
				<button>
					<label htmlFor="input-image-from-pc">
						{'Upload an image'}
					</label>
				</button>
			</div>
		)
	}
}

export {
	Toolbar,
}