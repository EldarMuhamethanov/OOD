import {Signal} from "../Signal";
import {ShapeType} from "../ShapeType";
import {ButtonRenderer} from "../button/ButtonRenderer";


class ToolbarRenderer {
    private toolbarHTML = document.createElement('div')
    private onCreateShapeSignal = new Signal<ShapeType>()
    private onDeleteShapeSignal = new Signal<void>()

    private m_createRectangleButton: ButtonRenderer
    private m_createTriangleButton: ButtonRenderer
    private m_createEllipseButton: ButtonRenderer
    private m_onDeleteShapeButton: ButtonRenderer

     constructor() {
        this.m_createRectangleButton = new ButtonRenderer('Rect', ['button'])
        this.m_createRectangleButton.getOnClickSignal().add(() => this.onCreateShapeSignal.dispatch('rectangle'))

        this.m_createTriangleButton = new ButtonRenderer('Triangle', ['button'])
        this.m_createTriangleButton.getOnClickSignal().add(() => this.onCreateShapeSignal.dispatch('triangle'))

        this.m_createEllipseButton = new ButtonRenderer('Ellipse', ['button'])
        this.m_createEllipseButton.getOnClickSignal().add(() => this.onCreateShapeSignal.dispatch('ellipse'))

        this.m_onDeleteShapeButton = new ButtonRenderer('Delete', ['button'])
        this.m_onDeleteShapeButton.getOnClickSignal().add(() => this.onDeleteShapeSignal.dispatch())
    }

    getOnCreateShapeSignal() {
        return this.onCreateShapeSignal
    }

    getOnDeleteShapeSignal() {
        return this.onDeleteShapeSignal
    }

    render(parentElement: HTMLElement) {
        this.toolbarHTML.innerHTML = ''
        this.toolbarHTML.classList.add('toolbar')

        this.m_createRectangleButton.render(this.toolbarHTML)
        this.m_createEllipseButton.render(this.toolbarHTML)
        this.m_createTriangleButton.render(this.toolbarHTML)
        this.m_onDeleteShapeButton.render(this.toolbarHTML)

        parentElement.appendChild(this.toolbarHTML)
    }
}

export {
    ToolbarRenderer,
}