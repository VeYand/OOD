import {createRoot} from 'react-dom/client'
import {EvaluatorDocument, StrategySum} from './document/EvaluatorDocument'
import {SummerView1, SummerView2} from './view/SummerView1'

const root = document.getElementById('root')

const evaluationStrategy = new StrategySum()
const documentModel = new EvaluatorDocument(evaluationStrategy)

if (root) {
	createRoot(root).render(
		<div>
			<div style={{display: 'flex', gap: 10}}>
				<SummerView1 document={documentModel}/>
				<SummerView2 document={documentModel}/>
			</div>
		</div>,
	)
}
