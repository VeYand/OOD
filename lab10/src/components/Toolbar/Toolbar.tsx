import {ChangeEvent, Component} from 'react'
import {CanvasController} from '../../controllers/CanvasController'
import {ArtObjectType} from '../../types/shapes'

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
		</div>
	)

	private renderCreateArtObjectBlock(): JSX.Element {
		const onCreateArt = (type: ArtObjectType) => {
			this.controller.addArtObject(type)
		}

		return (
			<div style={{display: 'flex', gap: '10px', padding: '10px', background: '#f4f4f4'}}>
				<button onClick={() => onCreateArt('rectangle')}>{'Rectangle'}</button>
				<button onClick={() => onCreateArt('triangle')}>{'Triangle'}</button>
				<button onClick={() => onCreateArt('ellipse')}>{'Ellipse'}</button>
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
			<div>
				<h3>{'Upload an image'}</h3>
				<input
					id="input-image-from-pc"
					type="file"
					accept=".jpeg, .jpg, .png"
					onChange={handleImageUpload}
				/>
				<div>
					<label htmlFor="input-image-from-pc">Select a file</label>
				</div>
			</div>
		)
	}
}

export {
	Toolbar,
}