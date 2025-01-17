type IEvaluatorListener = (firstValue: number, secondValue: number, result: number) => void

type IEvaluationStrategy = {
	execute: (firstValue: number, secondValue: number) => number,
}

class StrategySum implements IEvaluationStrategy {
	execute(firstValue: number, secondValue: number): number {
		return firstValue + secondValue
	}
}

class EvaluatorDocument {
	private m_firstValue = 87
	private m_secondValue = 0
	private m_result = 0
	private m_evaluationStrategy: IEvaluationStrategy
	private listeners: IEvaluatorListener[] = []

	constructor(strategy: IEvaluationStrategy) {
		this.m_evaluationStrategy = strategy
	}

	registerListener(listener: IEvaluatorListener): void {
		this.listeners.push(listener)
	}

	unregisterListener(listener: IEvaluatorListener): void {
		this.listeners = this.listeners.filter(l => l !== listener)
	}

	setStrategy(strategy: IEvaluationStrategy): void {
		this.m_evaluationStrategy = strategy
	}

	evaluate(firstValue: number, secondValue: number): void {
		this.m_firstValue = firstValue
		this.m_secondValue = secondValue

		this.m_result = this.m_evaluationStrategy.execute(firstValue, secondValue)
		this.notifyListeners(this.m_result)
	}

	getFirstValue(): number {
		return this.m_firstValue
	}

	getSecondValue(): number {
		return this.m_secondValue
	}

	getResult(): number {
		return this.m_result
	}

	private notifyListeners(result: number): void {
		for (const listener of this.listeners) {
			listener(this.m_firstValue, this.m_secondValue, result)
		}
	}
}

export type {IEvaluatorListener, IEvaluationStrategy}
export {StrategySum, EvaluatorDocument}
