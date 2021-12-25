import {Shape} from "../model/Shape";
import {ShapeController} from "../controller/ShapeController";
import {DragNDropHandler} from "../handlers/DragNDropHandler";
import {Signal} from "../common/Signal";
import {CanvasRenderer} from "./CanvasRenderer";
import {Renderer} from "./Renderer";
import { TagName } from "../common/TagName";


abstract class ShapeRenderer
{
    private m_renderer: Renderer = new Renderer(TagName.DIV)
    private readonly m_model: Shape
    private readonly m_controller: ShapeController
    private m_svgElement: SVGGraphicsElement = document.createElementNS('http://www.w3.org/2000/svg', 'svg')
    private onSelectSignal = new Signal<void>()

    protected constructor(model: Shape) {
        this.m_renderer.addClassName('shape')

        this.m_model = model
        this.m_controller = new ShapeController(model, this)

        this.m_model.getOnRectChange().add(() => this.rerender())
    }

    getOnSelectSignal() {
        return this.onSelectSignal
    }

    get model() {
        return this.m_model
    }

    get controller() {
        return this.m_controller
    }

    get renderer() {
        return this.m_renderer
    }

    protected abstract getShapeHtmlImpl(): SVGGraphicsElement

    private rerender() {
        const left = this.m_model.left
        const top = this.m_model.top
        const width = this.m_model.width
        const height = this.m_model.height

        this.m_renderer.setStyle('left', `${left}px`)
        this.m_renderer.setStyle('top', `${top}px`)
        this.m_renderer.setStyle('width', `${width}px`)
        this.m_renderer.setStyle('height', `${height}px`)

        this.m_svgElement.setAttribute('viewPort', `0 0 ${width} ${height}`)
        this.m_svgElement.innerHTML = ''
        const impl = this.getShapeHtmlImpl()
        this.m_svgElement.appendChild(impl)
    }

    render(parentElement: HTMLElement) {
        this.m_renderer.removeFromDom()
        this.m_svgElement.setAttribute('xmlns', 'http://www.w3.org/2000/svg')
        this.m_svgElement.setAttribute('width', '100%')
        this.m_svgElement.setAttribute('height', '100%')
        this.rerender()

        const shapeHTML = this.m_renderer.getDomElement()

        const dndHandler = new DragNDropHandler(shapeHTML)
        dndHandler.getOnMoveSignal().add(newPosition => {
            const parentBounds = parentElement.getBoundingClientRect()
            this.m_controller.shapeMove({
                left: newPosition.left - parentBounds.left,
                top: newPosition.top - parentBounds.top,
            })
        })

        this.m_renderer.addEventListener('mousedown', e => {
            e.preventDefault()
            this.onSelectSignal.dispatch()
        })

        this.m_renderer.appendChild(this.m_svgElement)
        parentElement.appendChild(shapeHTML)
    }
}

export {
    ShapeRenderer,
}