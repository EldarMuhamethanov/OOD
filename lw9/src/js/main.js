"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var EditorModel_1 = require("./editor/EditorModel");
var EditorRenderer_1 = require("./editor/EditorRenderer");
function startApp() {
    var editor = new EditorModel_1.EditorModel();
    var editorRenderer = new EditorRenderer_1.EditorRenderer(editor);
    editorRenderer.render();
}
window.onload = function () {
    startApp();
};
//# sourceMappingURL=main.js.map