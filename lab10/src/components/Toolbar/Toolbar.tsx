// import ellipse from 'svg/ellipse.svg'
// import rectangle from 'svg/rectangle.svg'
// import triangle from 'svg/triangle.svg'


import {ChangeEvent} from 'react'
import {CanvasController} from '../../controllers/CanvasController'
import {ArtObjectType} from '../../types/shapes'

type ToolbarProps = {
	controller: CanvasController,
}

type CreateArtObjectBlockProps = {
	onCreateArt: (type: ArtObjectType) => void,
}

type ImageImportBlockProps = {
	onCreateImage: (data: string) => void,
}

const CreateArtObjectBlock = ({onCreateArt}: CreateArtObjectBlockProps) => (
	<div style={{display: 'flex', gap: '10px', padding: '10px', background: '#f4f4f4'}}>
		<button onClick={() => onCreateArt('rectangle')}>
			{/*<img src={rectangle}></img>*/}
			{'Rectangle'}
		</button>
		<button onClick={() => onCreateArt('triangle')}>
			{/*<img src={triangle}></img>*/}
			{'Triangle'}
		</button>
		<button onClick={() => onCreateArt('ellipse')}>
			{/*<img src={ellipse}></img>*/}
			{'Ellipse'}
		</button>
	</div>
)

const handleImageUpload = (
	e: ChangeEvent<HTMLInputElement>,
	onCreateImage: (data: string) => void,
) => {
	const file = e.target.files?.[0]

	if (!file) {
		return
	}

	const reader = new FileReader()
	reader.onload = event => {
		onCreateImage((event.target?.result ?? '') as string)
	}
	reader.readAsDataURL(file)
}

const ImageImportBlock = ({onCreateImage}: ImageImportBlockProps) => (
	<div>
		<h3>{'Upload an image'}</h3>
		<input
			id="input-image-from-pc"
			type="file"
			accept=".jpeg, .jpg, .png"
			onChange={e => handleImageUpload(e, onCreateImage)}
		/>
		<div>
			<label htmlFor="input-image-from-pc">Select a file</label>
		</div>
	</div>
)

const Toolbar = ({controller}: ToolbarProps) => {
	const onCreateArt = (type: ArtObjectType) => {
		controller.addArtObject(type)
	}

	const onCreateImage = (data: string) => {
		controller.addImage(data)
	}

	return (
		<div style={{display: 'flex', gap: '10px'}}>
			<CreateArtObjectBlock onCreateArt={onCreateArt}/>
			<ImageImportBlock onCreateImage={onCreateImage}/>
		</div>
	)
}

export {
	Toolbar,
}