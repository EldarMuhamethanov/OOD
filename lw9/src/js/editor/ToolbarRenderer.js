"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ToolbarRenderer = void 0;
var Signal_1 = require("../Signal");
var ButtonRenderer_1 = require("../button/ButtonRenderer");
var ToolbarRenderer = /** @class */ (function () {
    function ToolbarRenderer() {
        var _this = this;
        this.toolbarHTML = document.createElement('div');
        this.onCreateShapeSignal = new Signal_1.Signal();
        this.onDeleteShapeSignal = new Signal_1.Signal();
        this.m_createRectangleButton = new ButtonRenderer_1.ButtonRenderer('Rect', ['button']);
        this.m_createRectangleButton.getOnClickSignal().add(function () { return _this.onCreateShapeSignal.dispatch('rectangle'); });
        this.m_createTriangleButton = new ButtonRenderer_1.ButtonRenderer('Triangle', ['button']);
        this.m_createTriangleButton.getOnClickSignal().add(function () { return _this.onCreateShapeSignal.dispatch('triangle'); });
        this.m_createEllipseButton = new ButtonRenderer_1.ButtonRenderer('Ellipse', ['button']);
        this.m_createEllipseButton.getOnClickSignal().add(function () { return _this.onCreateShapeSignal.dispatch('ellipse'); });
        this.m_onDeleteShapeButton = new ButtonRenderer_1.ButtonRenderer('Delete', ['button']);
        this.m_onDeleteShapeButton.getOnClickSignal().add(function () { return _this.onDeleteShapeSignal.dispatch(); });
    }
    ToolbarRenderer.prototype.getOnCreateShapeSignal = function () {
        return this.onCreateShapeSignal;
    };
    ToolbarRenderer.prototype.getOnDeleteShapeSignal = function () {
        return this.onDeleteShapeSignal;
    };
    ToolbarRenderer.prototype.render = function (parentElement) {
        this.toolbarHTML.innerHTML = '';
        this.toolbarHTML.classList.add('toolbar');
        this.m_createRectangleButton.render(this.toolbarHTML);
        this.m_createEllipseButton.render(this.toolbarHTML);
        this.m_createTriangleButton.render(this.toolbarHTML);
        this.m_onDeleteShapeButton.render(this.toolbarHTML);
        parentElement.appendChild(this.toolbarHTML);
    };
    return ToolbarRenderer;
}());
exports.ToolbarRenderer = ToolbarRenderer;
//# sourceMappingURL=ToolbarRenderer.js.map