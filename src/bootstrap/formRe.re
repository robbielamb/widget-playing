include Utils;

include Colors;

let component = ReasonReact.statelessComponent "Form";

let make
    tag::(tag: string)="form"
    inline::(inline: bool)=false
    className::(className: option string)=?
    children => {
  ...component,
  render: fun _self => {
    let classes = [unwrapStr i className, inline ? "form-inline" : ""] |> String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  }
};

module Feedback = {};

module Group = {
  let component = ReasonReact.statelessComponent "Form.Group";
  let make
      tag::(tag: string)="div"
      row::(row: bool)=false
      disabled::(disabled: bool)=false
      inline::(inline: bool)=false
      className::(className: option string)=?
      children => {
    ...component,
    render: fun _self => {
      let classes =
        [unwrapStr i className, "form-group", row ? "row" : "", disabled ? "disabled" : ""] |>
        String.concat " ";
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module Check = {
  let component = ReasonReact.statelessComponent "Form.Group";
  let make
      tag::(tag: string)="div"
      row::(row: bool)=false
      inline::(inline: bool)=false
      disabled::(disabled: bool)=false
      className::(className: option string)=?
      children => {
    ...component,
    render: fun _self => {
      let classes =
        [
          unwrapStr i className,
          "form-check",
          row ? "row" : "",
          inline ? "form-check-inline" : "",
          disabled ? "disabled" : ""
        ] |>
        String.concat " ";
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module Text = {
  let component = ReasonReact.statelessComponent "Form.Text";
  let make
      tag::(tag: string)="small"
      inline::(inline: bool)=false
      color::(color: TextColor.t)=TextColor.Muted
      className::(className: option string)=?
      children => {
    ...component,
    render: fun _self => {
      let classes =
        [unwrapStr i className, not inline ? "form-text" : "", TextColor.toString color] |>
        String.concat " ";
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

/* Should this just be a Label? Should we have an Input doo dad with an Input.Label? Then perhaps an Input.Text? */
