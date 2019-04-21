include Utils;


[@react.component]
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
      ~children=[|React.null|],
    ) => {
    let percent = Js.Float.toString(value /. max *. 100.0) ++ "0%";
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
      <div
        
            className= progressBarClasses
            style= ReactDOMRe.Style.make(~width=percent, ())
            //ariavaluenow= value
            ariaValuenow=value
            ariaValuemin= 0.0
            ariaValuemax= max
          >
        (React.array(children))
      </div>;
 
   /*  let wrapper =
      ReactDOMRe.createElementVariadic(
        tag,
        ~props=
          {"className": progressClasses, "role": "progressbar"}
          ->ReactDOMRe.objToDOMProps,
      ); */
    switch (multi, bar) {
    | (true, true) => React.array(children) /*** This option doesn't actually make sense. */
    | (true, false) => <div className=progressClasses role="progressbar"> (React.array(children)) </div>
    | (false, true) => progressBar
    | (false, false) =>  <div className=progressClasses role="progressbar"> progressBar </div>
    };
  
};



