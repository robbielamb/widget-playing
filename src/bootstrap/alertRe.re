include Utils;

module Color = {
    type t =
      | Primary
      | Success
      | Info
      | Warning
      | Danger;
    let toString color =>
      switch color {
      | Primary => "primary"
      | Success => "success"
      | Info => "info"
      | Warning => "warning"
      | Danger => "danger"
      };
  };
  let onEnter _el _isAppearing => Js.log "onEnter";
  let component = ReasonReact.statelessComponent "Alert";
  let make
      className::(className: option string)=?
      closeClassName::(closeClassName: option string)=?
      color::(color: Color.t)=Color.Success
      isOpen::(isOpen: bool)=true
      toggle::(toggle: option (ReactEventRe.Mouse.t => unit))=?
      tag::(tag: string)="div"
      closeAriaLabel::(closeAriaLabel: string)="Close"
      ::transitionAppearTimeout=150
      ::transitionEnterTimeout=150
      ::transitionLeaveTimeout=150
      cssModule::(cssModule: option (Js.t {..}))=?
      children => {
    ...component,
    render: fun _self => {
      let closeClasses = classNameReduce closeClassName [cn "close"];
      let (toggleElement, toggleEnabled) =
        switch toggle {
        | None => (ReasonReact.nullElement, false)
        | Some cb => (
            ReasonReact.createDomElement
              "button"
              props::{
                "type": "button",
                "className": closeClasses,
                "onClick": cb,
                "aria-label": closeAriaLabel
              }
              [|
                ReasonReact.createDomElement
                  "span"
                  props::{"aria-hidden": "true"}
                  [|ReasonReact.stringToElement (Js.String.fromCharCode 215)|]
              |],
            true
          )
        };
      let _ = Js.Array.unshift toggleElement children;
      let classes = classNameReduce className [cn "alert", cn ("alert-" ^ Color.toString color)];
      let alert = ReasonReact.createDomElement tag props::{"className": classes} children;
      let visible = isOpen ? alert : <span />;
      /* visible */
      let fade = "fade";
      let show = "show";
      visible
      /* TODO: Make this work with an animation */
      /* <Transition.Transition
            onEnter=(onEnter)
            timeout=500 _in=isOpen>
           visible
         </Transition.Transition> */
    }
  };