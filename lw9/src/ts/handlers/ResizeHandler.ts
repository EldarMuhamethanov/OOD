import { Rect } from "../common/Rect";
import {ISignal, Signal} from "../common/Signal";
import { TagName } from "../common/TagName";

const HANDLER_SIDE_SIZE = 10
const MIN_WIDTH = 20
const MIN_HEIGHT = 20

type HandlerType = 'leftTop' | 'rightTop' | 'leftBottom' | 'rightBottom'

type CoordinatesRect = {
    left: number,
    top: number,
    right: number,
    bottom: number,
}

class ResizeHandler {
    private m_element: HTMLElement
    private onRectChangeSignal: ISignal<Rect> = new Signal<Rect>()

    private windowMouseMoveHandler: (e: MouseEvent) => void = () => {}
    private windowMouseUpHandler: (e: MouseEvent) => void = () => {}

    constructor(element: HTMLElement) {
        this.m_element = element
        this.addResizeHandlers()
    }

    getOnRectChangeSignal() {
        return this.onRectChangeSignal
    }

    private customizeControllers(handler: HTMLElement, handlerType: HandlerType) {
        handler.style.width = `${HANDLER_SIDE_SIZE}px`
        handler.style.height = `${HANDLER_SIDE_SIZE}px`
        handler.style.position = 'absolute'
        handler.style.background = 'blue'
        handler.style.pointerEvents = 'all'

        const offset = `-${HANDLER_SIDE_SIZE / 2}px`
        if (handlerType === 'leftBottom') {
            handler.style.bottom = offset
            handler.style.left = offset
        }
        else if (handlerType === 'leftTop') {
            handler.style.top = offset
            handler.style.left = offset
        }
        else if (handlerType === 'rightBottom') {
            handler.style.bottom = offset
            handler.style.right = offset
        }
        else if (handlerType === 'rightTop') {
            handler.style.top = offset
            handler.style.right = offset
        }

        this.subscribeOnDnd(handler, handlerType)
    }

    private handleMouseUp() {
        window.removeEventListener('mousemove', this.windowMouseMoveHandler)
        window.removeEventListener('mouseup', this.windowMouseUpHandler)
    }

    private handlerMouseMove(e: MouseEvent, type: HandlerType, startRect: CoordinatesRect) {
        const mouseLeft = e.clientX
        const mouseTop = e.clientY
        const elementBounds = this.m_element.getBoundingClientRect()
        if (type === "leftTop") {
            const left = Math.min(mouseLeft, startRect.right - MIN_WIDTH)
            const top = Math.min(mouseTop, startRect.bottom - MIN_HEIGHT)
            this.onRectChangeSignal.dispatch({
                left,
                top,
                width: elementBounds.right - left,
                height: elementBounds.bottom - top,
            })
        }
        else if (type === "rightTop") {
            const top = Math.min(mouseTop, startRect.bottom - MIN_HEIGHT)
            this.onRectChangeSignal.dispatch({
                left: elementBounds.left,
                top,
                width: Math.max(mouseLeft - elementBounds.left, MIN_WIDTH),
                height: elementBounds.bottom - top,
            })
        }
        else if (type === "leftBottom") {
            const left = Math.min(mouseLeft, startRect.right - MIN_WIDTH)
            this.onRectChangeSignal.dispatch({
                left,
                top: elementBounds.top,
                width: elementBounds.right - left,
                height: Math.max(mouseTop - elementBounds.top, MIN_HEIGHT),
            })
        }
        else if (type === "rightBottom") {
            this.onRectChangeSignal.dispatch({
                left: elementBounds.left,
                top: elementBounds.top,
                width: Math.max(mouseLeft - elementBounds.left, MIN_WIDTH),
                height: Math.max(mouseTop - elementBounds.top, MIN_HEIGHT),
            })
        }
    }

    private subscribeOnDnd(controller: HTMLElement, type: HandlerType) {
        controller.onmousedown = (e) => {
            e.preventDefault()
            const elementsBounds = this.m_element.getBoundingClientRect()
            this.windowMouseMoveHandler = (e) => this.handlerMouseMove(e, type, {
                left: elementsBounds.left,
                top: elementsBounds.top,
                bottom: elementsBounds.bottom,
                right: elementsBounds.right,
            })
            this.windowMouseUpHandler = () => this.handleMouseUp()

            window.addEventListener('mousemove', this.windowMouseMoveHandler)
            window.addEventListener('mouseup', this.windowMouseUpHandler)
        }
    }

    private addResizeHandlers() {
        const leftTopResizeController = document.createElement(TagName.DIV)
        const rightTopResizeController = document.createElement(TagName.DIV)
        const leftBottomResizeController = document.createElement(TagName.DIV)
        const rightBottomResizeController = document.createElement(TagName.DIV)

        this.customizeControllers(leftTopResizeController, 'leftTop')
        this.customizeControllers(rightTopResizeController, 'rightTop')
        this.customizeControllers(leftBottomResizeController, 'leftBottom')
        this.customizeControllers(rightBottomResizeController, 'rightBottom')

        this.m_element.appendChild(leftTopResizeController)
        this.m_element.appendChild(rightTopResizeController)
        this.m_element.appendChild(leftBottomResizeController)
        this.m_element.appendChild(rightBottomResizeController)
    }
}

export {
    ResizeHandler,
}