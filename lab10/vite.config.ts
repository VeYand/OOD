import * as path from 'path'
import url from 'url'
import {ConfigEnv} from 'vite'
import {buildViteConfig} from './config/build/buildViteConfig'
import {BuildAliases, BuildMode, BuildPaths} from './config/build/types/config'

const __filename = url.fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

export default (configEnv: ConfigEnv) => {
	const mode = (configEnv.mode ?? 'development') as BuildMode
	const isDev = mode === 'development'
	const paths: BuildPaths = {
		html: '',
		entry: path.resolve(__dirname, 'src', 'main.tsx'),
	}

	const aliases: BuildAliases = {
		shared: path.resolve(__dirname, 'src', 'shared'),
		pages: path.resolve(__dirname, 'src', 'pages'),
		widgets: path.resolve(__dirname, 'src', 'widgets'),
		features: path.resolve(__dirname, 'src', 'features'),
		entities: path.resolve(__dirname, 'src', 'entities'),
		app: path.resolve(__dirname, 'src', 'app'),
	}

	return buildViteConfig({
		isDev,
		mode,
		paths,
		aliases,
		port: 3000,
	})
}
