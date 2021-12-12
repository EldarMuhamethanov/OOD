import { Rect } from "../shapes/Rect";
import {ISignal, Signal} from "../Signal";

const HANDLER_SIDE_SIZE = 10

type HandlerType = 'leftTop' | 'rightTop' | 'leftBottom' | 'rightBottom'

class ResizeHandler {
    private m_element: HTMLElement
    private onRectChangeSignal: ISignal<Rect> = new Signal<Rect>()

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
        window.onmousemove = null
        window.onmouseup = null
    }

    private handlerMouseMove(e: MouseEvent, type: HandlerType) {
        const mouseLeft = e.clientX
        const mouseTop = e.clientY
        const elementBounds = this.m_element.getBoundingClientRect()
        if (type === "leftTop") {
            this.onRectChangeSignal.dispatch({
                left: mouseLeft,
                top: mouseTop,
                width: elementBounds.right - mouseLeft,
                height: elementBounds.bottom - mouseTop,
            })
        }
        else if (type === "rightTop") {
            this.onRectChangeSignal.dispatch({
                left: elementBounds.left,
                top: mouseTop,
                width: mouseLeft - elementBounds.left,
                height: elementBounds.bottom - mouseTop,
            })
        }
        else if (type === "leftBottom") {
            this.onRectChangeSignal.dispatch({
                left: mouseLeft,
                top: elementBounds.top,
                width: elementBounds.right - mouseLeft,
                height: mouseTop - elementBounds.top,
            })
        }
        else if (type === "rightBottom") {
            this.onRectChangeSignal.dispatch({
                left: elementBounds.left,
                top: elementBounds.top,
                width: mouseLeft - elementBounds.left,
                height: mouseTop - elementBounds.top,
            })
        }
    }

    private subscribeOnDnd(controller: HTMLElement, type: HandlerType) {
        controller.onmousedown = (e) => {
            e.preventDefault()
            window.onmousemove = e => this.handlerMouseMove(e, type)
            window.onmouseup = () => this.handleMouseUp()
        }
    }

    private addResizeHandlers() {
        const leftTopResizeController = document.createElement('div')
        const rightTopResizeController = document.createElement('div')
        const leftBottomResizeController = document.createElement('div')
        const rightBottomResizeController = document.createElement('div')

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