import {createRoot} from 'react-dom/client'
import {App} from './components/App'

const root = document.getElementById('root')

if (root) {
	createRoot(root).render(
		<App/>,
	)
}

//todo маркеры выделения и рамка на верхенм слое
//todo фигура привязана к курсору
//todo фигуру можно выделить только за внутреннюю область

//todo не отдавать внутренние струкутры данных наружу

// todo можно разделить контроллер наhape

//todo подумать над более точечным обновлением
//todo попробовать сделать 2-е вьюшки, поправить