include Utils;

let component = ReasonReact.statelessComponent("Progress");

let make =
    (
      ~tag: string="div",
      ~multi: bool=false,
      ~bar: bool=false,
      ~value: float=0.0,
      ~max: float=100.0,
      ~animated: bool=false,
      ~striped: bool=false,
      ~color: option(ColorsRe.Background.t)=?,
      ~className: option(string)=?,
      /* barClassName::(barClassName: option string)=? */
      children,
    ) => {
  ...component,
  render: _self => {
    let percent = string_of_float(value /. max *. 100.0) ++ "0%";
    let progressClasses =
      ["progress", unwrapStr(i, className)] |> String.concat(" ");
    let progressBarClasses =
      [
        "progress-bar",
        animated ? "progress-bar-animated" : "",
        ColorsRe.Background.unWrap(color),
        animated || striped ? "progress-bar-striped" : "",
        unwrapStr(i, className),
      ]
      |> String.concat(" ");
    let progressBar =
      ReactDOMRe.createElementVariadic(
        "div",
        ~props={
          "className": progressBarClasses,
          "style": ReactDOMRe.Style.make(~width=percent, ()),
          "aria-valuenow": value,
          "aria-valuemin": 0,
          "aria-valuemax": max,
        } |. ReactDOMRe.objToDOMProps,
        children,
      );
    let wrapper =
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": progressClasses, "role": "progressbar"} |. ReactDOMRe.objToDOMProps,
      );
    switch (multi, bar) {
    | (true, true) => ReasonReact.array(children) /*** This option doesn't actually make sense. */
    | (true, false) => wrapper(children)
    | (false, true) => progressBar
    | (false, false) => wrapper([|progressBar|])
    };
  },
};
