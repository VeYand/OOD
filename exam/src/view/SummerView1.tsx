import React, {Component} from 'react'
import {EvaluatorDocument} from '../document/EvaluatorDocument'

type SummerViewProps = {
	document: EvaluatorDocument,
}

type SummerViewState = {
	firstValue: number,
	secondValue: number,
	result: number,
}

class SummerView1 extends Component<SummerViewProps, SummerViewState> {
	constructor(props: SummerViewProps) {
		super(props)
		this.state = {
			firstValue: this.props.document.getFirstValue(),
			secondValue:  this.props.document.getSecondValue(),
			result: this.props.document.getResult(),
		}
	}

	override componentDidMount() {
		this.props.document.registerListener(this.documentChangeListener)
	}

	override componentWillUnmount() {
		this.props.document.unregisterListener(this.documentChangeListener)
	}

	handleValueChange = (event: React.ChangeEvent<HTMLInputElement>, valueType: 'first' | 'second') => {
		const value = Number(event.target.value)
		if (valueType === 'first') {
			this.setState({firstValue: value}, () => {
				this.props.document.evaluate(this.state.firstValue, this.state.secondValue)
			})
		}
		else {
			this.setState({secondValue: value}, () => {
				this.props.document.evaluate(this.state.firstValue, this.state.secondValue)
			})
		}
	}

	documentChangeListener = (firstValue: number, secondValue: number, result: number) => {
		this.setState({firstValue, secondValue, result})
	}

	override render() {
		return (
			<div style={{display: 'flex', flexDirection: 'column', gap: '10px'}}>
				<input
					type="number"
					value={this.state.firstValue}
					onChange={event => this.handleValueChange(event, 'first')}
					placeholder="Введите первое число"
				/>
				<input
					type="number"
					value={this.state.secondValue}
					onChange={event => this.handleValueChange(event, 'second')}
					placeholder="Введите второе число"
				/>
				<div>Результат: {this.state.result}</div>
			</div>
		)
	}
}

class SummerView2 extends Component<SummerViewProps, SummerViewState> {
	constructor(props: SummerViewProps) {
		super(props)
		this.state = {
			firstValue: this.props.document.getFirstValue(),
			secondValue:  this.props.document.getSecondValue(),
			result: this.props.document.getResult(),
		}
	}

	override componentDidMount() {
		this.props.document.registerListener(this.documentChangeListener)
	}

	override componentWillUnmount() {
		this.props.document.unregisterListener(this.documentChangeListener)
	}

	handleValueChange = (event: React.ChangeEvent<HTMLInputElement>, valueType: 'first' | 'second') => {
		const value = Number(event.target.value)
		if (valueType === 'first') {
			this.setState({firstValue: value}, () => {
				this.props.document.evaluate(this.state.firstValue, this.state.secondValue)
			})
		}
		else {
			this.setState({secondValue: value}, () => {
				this.props.document.evaluate(this.state.firstValue, this.state.secondValue)
			})
		}
	}

	documentChangeListener = (firstValue: number, secondValue: number, result: number) => {
		this.setState({firstValue, secondValue, result})
	}

	override render() {
		return (
			<div style={{display: 'flex', flexDirection: 'row', gap: '10px'}}>
				<input
					type="number"
					value={this.state.firstValue}
					onChange={event => this.handleValueChange(event, 'first')}
					placeholder="Введите первое число"
				/>
				<input
					type="number"
					value={this.state.secondValue}
					onChange={event => this.handleValueChange(event, 'second')}
					placeholder="Введите второе число"
				/>
				<div>Результат: {this.state.result}</div>
			</div>
		)
	}
}

export {SummerView1, SummerView2}
