"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ButtonRenderer = void 0;
var Signal_1 = require("../Signal");
var ButtonRenderer = /** @class */ (function () {
    function ButtonRenderer(text, classList) {
        var _this = this;
        this.buttonHTML = document.createElement('button');
        this.onClickSignal = new Signal_1.Signal();
        this.m_text = text;
        classList.forEach(function (className) { return _this.buttonHTML.classList.add(className); });
    }
    ButtonRenderer.prototype.getOnClickSignal = function () {
        return this.onClickSignal;
    };
    ButtonRenderer.prototype.render = function (parentElement) {
        var _this = this;
        this.buttonHTML.innerHTML = this.m_text;
        this.buttonHTML.onclick = function () { return _this.onClickSignal.dispatch(); };
        parentElement.appendChild(this.buttonHTML);
    };
    return ButtonRenderer;
}());
exports.ButtonRenderer = ButtonRenderer;
//# sourceMappingURL=ButtonRenderer.js.map