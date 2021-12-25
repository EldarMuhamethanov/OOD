import {ShapeFactory} from "../factory/ShapeFactory";
import {ShapeRenderer} from "./ShapeRenderer";
import {CanvasModel} from "../model/CanvasModel";
import {CanvasController} from "../controller/CanvasController";
import {SelectionView} from "./SelectionView";
import {Renderer} from "./Renderer";
import {TagName} from "../common/TagName";
import {Shape} from "../model/Shape";


type ShapeIdToRendererMapItem = {
    view: ShapeRenderer,
    unsubHandlers: Array<() => void>
}

class CanvasRenderer {
    private m_renderer: Renderer = new Renderer(TagName.DIV)
    private m_model: CanvasModel
    private m_controller: CanvasController

    private m_selectionView: SelectionView

    private m_shapeIdToRendererMap = new Map<string, ShapeIdToRendererMapItem>()

    constructor(model: CanvasModel) {
        this.m_renderer.addClassName('canvas')
        this.m_renderer.setStyle('width', `${model.getWidth()}px`)
        this.m_renderer.setStyle('height', `${model.getHeight()}px`)

        this.m_model = model
        this.m_controller = new CanvasController(model, this)

        this.m_selectionView = new SelectionView(
            model.getSelectionModel(),
            this.m_renderer.getDomElement(),
        )

        this.m_model.getShapes().forEach(shape => this.handleShapeCreate(shape))
        this.m_model.getOnShapeCreated().add(shape => this.handleShapeCreate(shape))

        this.m_model.getOnShapeRemoved().add(shapeId => this.handleShapeRemove(shapeId))

        this.m_renderer.addEventListener('mousedown', e => {
            if (!e.defaultPrevented) {
                this.m_controller.resetSelection()
            }
        })

        document.addEventListener('keydown', e => {
            const keyboardEvent = e as KeyboardEvent
            this.handleKeydownEvent(keyboardEvent)
        })
    }

    clear() {
        this.m_renderer.removeFromDom()
    }

    handleDeleteSelectedShape() {
        const selectedShape = this.m_model.getSelectionModel().getSelectedShape()
        if (selectedShape) {
            this.m_controller.removeShape(selectedShape.id)
        }
    }

    private handleKeydownEvent(e: KeyboardEvent) {
        if (e.key === 'Delete') {
            this.handleDeleteSelectedShape()
        }
    }

    private handleShapeCreate(shape: Shape) {
        const shapeRenderer = ShapeFactory.createShapeRenderer(shape)
        const unsub = shapeRenderer.getOnSelectSignal().add(() => this.m_controller.selectShape(shape))
        this.m_shapeIdToRendererMap.set(shape.id, {
            view: shapeRenderer,
            unsubHandlers: [unsub]
        })
        shapeRenderer.render(this.m_renderer.getDomElement())
    }

    private handleShapeRemove(shapeId: string) {
        const mapItem = this.m_shapeIdToRendererMap.get(shapeId)
        if (mapItem) {
            mapItem.view.renderer.removeFromDom()
            mapItem.unsubHandlers.forEach(unsubHandler => unsubHandler())
            this.m_shapeIdToRendererMap.delete(shapeId)
        }
    }

    render(parentElement: HTMLElement) {
        this.m_renderer.removeFromDom()
        parentElement.appendChild(this.m_renderer.getDomElement())
    }
}

export {
    CanvasRenderer,
}