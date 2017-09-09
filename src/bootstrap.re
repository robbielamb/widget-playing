module Alert = {
  external alert : ReasonReact.reactClass = "Alert" [@@bs.module "reactstrap"];
  type t =
    Js.t {
      .
      className : Js.undefined string,
      color : string, /* default 'success */
      isOpen : Js.boolean, /* default: true */
      toggle: Js.undefined (ReactEventRe.Mouse.t => unit),
      /* tag: ReactElement or string */
      transitionAppearTimeout : int,
      transitionEnterTimeout : int,
      transitionLeaveTimeout : int
    };
  module Color = {
    type t =
      | Success
      | Info
      | Warning
      | Danger;
    let toString color =>
      switch color {
      | Success => "success"
      | Info => "info"
      | Warning => "warning"
      | Danger => "danger"
      };
  };
  let make
      ::className=?
      ::color=Color.Success
      ::isOpen=true
      ::toggle=?
      ::transitionAppearTimeout=150
      ::transitionEnterTimeout=150
      ::transitionLeaveTimeout=150
      children =>
    ReasonReact.wrapJsForReason
      reactClass::alert
      props::({
        "className": Js.Undefined.from_opt className,
        "color": Color.toString color,
        "isOpen": Js.Boolean.to_js_boolean isOpen,
        "toggle": Js.Undefined.from_opt toggle,
        "transitionAppearTimeout" : transitionAppearTimeout,
        "transitionEnterTimeout" : transitionEnterTimeout,
        "transitionLeaveTimeout" : transitionLeaveTimeout
      } : t )
      children;
};