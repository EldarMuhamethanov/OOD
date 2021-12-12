import {Shape} from "./Shape";
import { ShapeController } from "./ShapeController";
import {DragNDropHandler, Position} from "../handlers/DragNDropHandler";
import {ResizeHandler} from "../handlers/ResizeHandler";
import {Rect} from "./Rect";
import {Signal} from "../Signal";
import {Canvas} from "../Canvas/Canvas";

const MIN_WIDTH = 20
const MIN_HEIGHT = 20

abstract class ShapeRenderer
{
    private readonly m_model: Shape
    private readonly m_controller: ShapeController
    private m_canvas: Canvas
    private m_element: HTMLElement = document.createElement('div')
    private onSelectSignal = new Signal<void>()

    protected constructor(model: Shape, canvas: Canvas) {
        this.m_model = model
        this.m_canvas = canvas
        this.m_controller = new ShapeController(model, this)

        this.m_model.getOnRectChange().add(() => this.rerender())
    }

    getOnSelectSignal() {
        return this.onSelectSignal
    }

    get model() {
        return this.m_model
    }

    setSelected(isSelected: boolean) {
        this.m_controller.setIsSelected(isSelected)
    }

    protected abstract getShapeHtmlImpl(): string

    private rerender() {
        const left = this.m_model.left
        const top = this.m_model.top
        const width = this.m_model.width
        const height = this.m_model.height
        this.m_element.style.left = `${left}px`
        this.m_element.style.top = `${top}px`
        this.m_element.style.width = `${width}px`
        this.m_element.style.height = `${height}px`
        this.m_element.style.position = 'absolute'

        this.m_element.style.boxShadow = this.m_model.isSelected
            ? '0 0 0 2px blue'
            : ''

        const svg = this.m_element.getElementsByTagName('svg')[0]
        if (svg) {
            svg.outerHTML = this.getShapeHtmlImpl()
        }
        else {
            this.m_element.innerHTML = this.getShapeHtmlImpl()
        }
    }

    private handleMove(position: Position, canvas: HTMLElement) {
        const canvasBounds = canvas.getBoundingClientRect()

        const left = position.left
        const top = position.top
        const width = this.m_model.width
        const height = this.m_model.height

        this.m_controller.setRect(
            Math.min(Math.max(left - canvasBounds.left, 0), canvasBounds.right - canvasBounds.left - width),
            Math.min(Math.max(top - canvasBounds.top, 0), canvasBounds.bottom - canvasBounds.top - height),
            width,
            height
        )
    }

    private handleResize(rect: Rect, canvas: HTMLElement) {
        const canvasBounds = canvas.getBoundingClientRect()

        const left = Math.max(rect.left, canvasBounds.left);
        const top = Math.max(rect.top, canvasBounds.top);
        const right = Math.min(rect.left + rect.width, canvasBounds.right);
        const bottom = Math.min(rect.top + rect.height, canvasBounds.bottom);

        this.m_controller.setRect(
            left - canvasBounds.left,
            top - canvasBounds.top,
            Math.max(right - left, MIN_WIDTH),
            Math.max(bottom - top, MIN_HEIGHT),
        )
    }

    render() {
        this.m_element.innerHTML = ''

        this.rerender()

        const canvasDomElement = this.m_canvas.getDomElement()

        if (this.m_model.isSelected) {
            const resizeHandler = new ResizeHandler(this.m_element)
            resizeHandler.getOnRectChangeSignal().add(rect => this.handleResize(rect, canvasDomElement))
        }

        const dndHandler = new DragNDropHandler(this.m_element)
        dndHandler.getOnMoveSignal().add(newPosition => this.handleMove(newPosition, canvasDomElement))
        dndHandler.getOnDragStart().add(() => this.onSelectSignal.dispatch())

        canvasDomElement.appendChild(this.m_element)
    }
}

export {
    ShapeRenderer,
}