include Utils;

module BackgroundColor = Colors.BackgroundColor;

let component = ReasonReact.statelessComponent "Progress";

let make
    tag::(tag: string)="div"
    multi::(multi: bool)=false
    bar::(bar: bool)=false
    value::(value: float)=0.0
    max::(max: float)=100.0
    animated::(animated: bool)=false
    striped::(striped: bool)=false
    color::(color: option BackgroundColor.t)=?
    className::(className: option string)=?
    /* barClassName::(barClassName: option string)=? */
    children => {
  ...component,
  render: fun _self => {
    let percent = string_of_float (value /. max *. 100.0) ^ "0%";
    let progressClasses = ["progress", unwrapStr i className] |> String.concat " ";
    let progressBarClasses =
      [
        "progress-bar",
        animated ? "progress-bar-animated" : "",
        BackgroundColor.unWrap color,
        animated || striped ? "progress-bar-striped" : "",
        unwrapStr i className
      ] |>
      String.concat " ";
    let progressBar =
      ReasonReact.createDomElement
        "div"
        props::{
          "className": progressBarClasses,
          "style": ReactDOMRe.Style.make width::percent (),
          "aria-valuenow": value,
          "aria-valuemin": 0,
          "aria-valuemax": max
        }
        children;
    let wrapper =
      ReasonReact.createDomElement
        tag props::{"className": progressClasses, "role": "progressbar"};
    switch (multi, bar) {
    | (true, true) => ReasonReact.arrayToElement children /** This option doesn't actually make sense. */
    | (true, false) => wrapper children
    | (false, true) => progressBar
    | (false, false) => wrapper [|progressBar|]
    }
  }
};