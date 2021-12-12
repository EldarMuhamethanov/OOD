import {Canvas} from "../Canvas/Canvas";
import {ToolbarRenderer} from "./ToolbarRenderer";
import {ShapeFactory} from "../Factory/ShapeFactory";
import {ShapeRenderer} from "../shapes/ShapeRenderer";
import {EditorModel} from "./EditorModel";
import {EditorController} from "./EditorController";
import {Shape} from "../shapes/Shape";


class EditorRenderer {
    private m_model: EditorModel
    private m_controller: EditorController
    private m_shapeIdToRendererMap: Map<string, ShapeRenderer> = new Map<string, ShapeRenderer>()
    private m_toolbarRenderer: ToolbarRenderer
    private readonly m_canvas: Canvas
    private editorHTML: HTMLElement = document.createElement('div')

    constructor(model: EditorModel) {
        this.m_model = model
        this.m_controller = new EditorController(model, this)

        this.m_model.getOnShapeCreated().add(shape => {
            const renderer = ShapeFactory.createShapeRenderer(shape, this.m_canvas)
            renderer.getOnSelectSignal().add(() => this.m_controller.setSelectedShape(shape.id))
            this.m_shapeIdToRendererMap.set(shape.id, renderer)
            this.render()
        })
        this.m_model.getOnShapeRemoved().add(shapeId => {
            this.m_shapeIdToRendererMap.delete(shapeId)
            this.render()
        })
        this.m_model.getOnSelectedShapeChanged().add(() => this.render())

        this.m_canvas = new Canvas()
        this.m_canvas.getOnCanvasClick().add(() => this.m_controller.setSelectedShape(null))

        this.m_toolbarRenderer = new ToolbarRenderer()
        this.m_toolbarRenderer.getOnCreateShapeSignal().add(shapeType => {
            this.addShape(ShapeFactory.createShapeModel(shapeType, this.m_canvas))
        })
        this.m_toolbarRenderer.getOnDeleteShapeSignal().add(() => this.removeShape())

        window.onkeydown = e => {
            if (e.key === 'Delete') {
                this.removeShape()
            }
        }
    }

    addShape(shapeModel: Shape) {
        this.m_controller.addShape(shapeModel)
    }

    removeShape() {
        this.m_controller.removeSelectedShape()
    }

    render() {
        this.editorHTML.innerHTML = ''
        this.editorHTML.classList.add('main-container')

        this.m_toolbarRenderer.render(this.editorHTML)

        const workspace = document.createElement('div')
        workspace.classList.add('workspace')
        this.m_canvas.render(workspace)
        this.editorHTML.appendChild(workspace)

        document.body.appendChild(this.editorHTML)

        this.m_model.getShapes().forEach(shape => {
            const shapeId = shape.id
            const shapeRenderer = this.m_shapeIdToRendererMap.get(shapeId)
            if (shapeRenderer) {
                shapeRenderer.setSelected(shapeId === this.m_model.getSelectedShape())
                shapeRenderer.render()
            }
        })
    }

}

export {
    EditorRenderer,
}